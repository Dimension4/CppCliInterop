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
        public string Type { get; }

        public ParameterInfo(string name, string type)
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

        public string ReturnType
        {
            get => GetValue<string>();
            set => SetValue(value);
        }

        public ObservableCollection<ParameterInfo> Parameters
        {
            get => GetValue<ObservableCollection<ParameterInfo>>();
            set => SetValue(value);
        }
    }
}