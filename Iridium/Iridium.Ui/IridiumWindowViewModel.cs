using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Iridium.Ui.Mvvm;

namespace Iridium.Ui
{
    public class OperationExecutionEventArgs : EventArgs
    {
        public string Name { get; }
        public object[] Arguments { get; }
        public object Result { get; set; }

        public OperationExecutionEventArgs(string name, object[] arguments)
        {
            Name = name;
            Arguments = arguments;
        }
    }

    public class IridiumWindowViewModel : ViewModelBase
    {
        public event EventHandler<OperationExecutionEventArgs> ExecuteOperation;

        public BitmapSource Image
        {
            get => GetValue<BitmapSource>();
            set => SetValue(value);
        }

        [DefaultValueIsInstance]
        public ObservableCollection<OperationTemplateViewModel> OperationTemplates
        {
            get => GetValue<ObservableCollection<OperationTemplateViewModel>>();
            set => SetValue(value);
        }

        public void RaiseExecuteOperation(OperationExecutionEventArgs e)
        {
            ExecuteOperation?.Invoke(this, e);
        }
    }
}
