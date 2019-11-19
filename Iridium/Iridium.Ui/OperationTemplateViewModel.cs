using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Iridium.Ui.Mvvm;

namespace Iridium.Ui
{
    public class ParameterInfo
    {
        public string Name { get; }
        public Type Type { get; }

        public ParameterInfo(string name, Type type)
        {
            Name = name;
            Type = type;
        }
    }

    public class OperationTemplateViewModel : ViewModelBase
    {
        public string Name
        {
            get => GetValue<string>();
            set => SetValue(value);
        }

        public string Description
        {
            get => GetValue<string>();
            set => SetValue(value);
        }

        public ReadOnlyObservableCollection<ParameterInfo> Parameters
        {
            get => GetValue<ReadOnlyObservableCollection<ParameterInfo>>();
            set => SetValue(value);
        }
    }
}