using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Iridium.Ui.Mvvm;

namespace Iridium.Ui
{
    public class IridiumWindowViewModel : ViewModelBase
    {
        [DefaultValueIsInstance]
        public ObservableCollection<OperationTemplateViewModel> OperationTemplates
        {
            get => GetValue<ObservableCollection<OperationTemplateViewModel>>();
            set => SetValue(value);
        }
    }
}
