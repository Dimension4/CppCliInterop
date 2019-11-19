using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.Serialization;

namespace Iridium.Ui.Mvvm
{
    public abstract class ViewModelBase : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private Dictionary<string, TypedValue> _data = new Dictionary<string, TypedValue>();
        private Dictionary<string, List<string>> _dependencies = new Dictionary<string, List<string>>();

        protected ViewModelBase()
        {
            Init(new StreamingContext());
        }

        [OnDeserializing]
        private void Init(StreamingContext context)
        {
            _data = new Dictionary<string, TypedValue>();
            _dependencies = new Dictionary<string, List<string>>();

            // SelfManagedAttribute on class level
            if (!(GetType().GetTypeInfo().GetCustomAttributes<SelfManagedAttribute>()?.Any() ?? true))
                BuildPropertyCache();

            BuildDependencyCache();
        }

        #region equality

        public bool Equals(ViewModelBase other)
        {
            if (GetType() != other.GetType() || _data.Count != other._data.Count)
                return false;

            foreach (var property in _data)
            {
                TypedValue value;
                if (!other._data.TryGetValue(property.Key, out value) || value.Value != property.Value.Value)
                    return false;
            }

            return true;
        }

        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj))
                return false;

            if (obj is ViewModelBase vm)
                return ReferenceEquals(this, vm) || Equals(vm);

            return false;
        }

        public override int GetHashCode()
        {
            return _data?.GetHashCode() ?? 0;
        }

        #endregion

        protected T GetValue<T>([CallerMemberName] string property = null)
        {
            if (!_data.TryGetValue(property, out TypedValue currentVal))
                throw new InvalidOperationException($"The property \"{property}\" is not cached and can not be get. " +
                                                    "Make sure neither the property nor the declaring type uses the SelfManaged attribute.");

            return (T) currentVal.Value;
        }

        protected bool SetValue<T>(T value, [CallerMemberName] string property = null)
        {
            if (!_data.TryGetValue(property, out TypedValue currentVal))
                throw new InvalidOperationException($"The property \"{property}\" is not cached and can not be set. " +
                                                    "Make sure neither the property nor the declaring type uses the SelfManaged attribute.");
            
            if ((value == null && currentVal.Value == null) || value != null && 
                (value.Equals(currentVal.Value) || !value.GetType().IsSubclassOf(currentVal.RootType) && value.GetType() != currentVal.RootType))
                return false;

            currentVal.Value = value;
            OnPropertyChanged(property);
            return true;
        }

        protected bool SetValue<T>(T value, ref T storage, [CallerMemberName] string property = null)
        {
            if (EqualityComparer<T>.Default.Equals(value, storage))
                return false;

            storage = value;
            OnPropertyChanged(property);
            return true;
        }

        protected bool SetValue<T>(T value, T oldValue, Action setAction, [CallerMemberName] string property = null)
        {
            if (EqualityComparer<T>.Default.Equals(value, oldValue))
                return false;

            setAction();
            OnPropertyChanged(property);
            return true;
        }

        protected virtual void OnPropertyChanged([CallerMemberName] string property = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(property));
            NotifyDependencies(property);
        }
        
        private void BuildPropertyCache()
        {
            foreach (var property in GetType().GetRuntimeProperties().Where(p => (!p.GetCustomAttributes<SelfManagedAttribute>()?.Any() ?? true) && p.SetMethod != null))
                _data.Add(property.Name, new TypedValue(property.PropertyType, GetDefault(property)));
        }

        private void BuildDependencyCache()
        {
            foreach (var property in GetType().GetRuntimeProperties().Where(p => !p.GetCustomAttributes<SelfManagedAttribute>()?.Any() ?? true))
            {
                var attr = property.GetCustomAttribute<DependsOnAttribute>();
                if (attr != null)
                {
                    foreach (var name in attr.Names.Distinct())
                    {
                        List<string> tmp;
                        if (_dependencies.ContainsKey(name))
                        {
                            tmp = _dependencies[name];
                        }
                        else
                        {
                            tmp = new List<string>();
                            _dependencies.Add(name, tmp);
                        }

                        tmp.Add(property.Name);
                    }
                }
            }

            var names = GetType().GetRuntimeProperties().Select(p => p.Name).ToArray();
            var deps = _dependencies.SelectMany(d => d.Value).Concat(_dependencies.Keys).Distinct().ToArray();

            var unknown = deps.FirstOrDefault(d => !names.Contains(d));
            if (unknown != null)
            {
                var sources = _dependencies.Where(d => d.Key == unknown).SelectMany(d => d.Value);
                throw new Exception($"Unresolved dependency injection detected. The unknown property \"{unknown}\" is referenced by " +
                                    $"these properties: {sources.Aggregate((n, t) => $"{t}, {n}")}.");
            }
        }

        private void NotifyDependencies(string property)
        {
            if (_dependencies.TryGetValue(property, out List<string> tmp))
                foreach (var dependency in tmp)
                    OnPropertyChanged(dependency);
        }


        private static object GetDefault(PropertyInfo property)
        {
            object value = property.GetCustomAttribute<DefaultValueAttribute>()?.Value;

            if (value == null)
            {
                var attr = property.GetCustomAttribute<DefaultValueIsInstanceAttribute>();

                if (attr != null)
                {
                    var ctors = property.PropertyType.GetTypeInfo().DeclaredConstructors.Where(c => c.IsPublic).Select(c => c.GetParameters()).ToArray();

                    // check if a valid ctor is exists
                    if (attr.Args == null && ctors.Any(c => c.Length == 0) ||
                        ctors.Any(param => param.Length == attr.Args.Length))
                    {
                        value = Activator.CreateInstance(property.PropertyType, attr.Args);
                    }
                    else
                    {
                        throw new InvalidOperationException($"The type \"{property.PropertyType.Name}\" of property \"{property.Name}\" has no public " +
                                                            $"constructor that accepts the arguments specified by the DefaultValueIsInstanceAttribute.");
                    }
                }
                else if (property.PropertyType.GetTypeInfo().IsValueType)
                {
                    value = Activator.CreateInstance(property.PropertyType);
                }
            }

            return value;
        }

        internal class TypedValue
        {
            public Type RootType { get; }

            public object Value { get; set; }

            public TypedValue(Type rootType, object value = null)
            {
                RootType = rootType;
                Value = value;
            }
        }
    }
}