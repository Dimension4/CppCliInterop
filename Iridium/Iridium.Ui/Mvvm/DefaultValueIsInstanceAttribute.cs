using System;

namespace Iridium.Ui.Mvvm
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DefaultValueIsInstanceAttribute : Attribute
    {
        public object[] Args { get; }

        public DefaultValueIsInstanceAttribute()
        {
            
        }

        public DefaultValueIsInstanceAttribute(params object[] constructorArguments)
        {
            Args = constructorArguments;
        }
    }
}