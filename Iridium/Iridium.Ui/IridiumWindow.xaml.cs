using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using Microsoft.Win32;

namespace Iridium.Ui
{
    /// <summary>
    /// Interaction logic for IridiumWindow.xaml
    /// </summary>
    public partial class IridiumWindow : Window
    {
        public static readonly DependencyProperty IridiumWindowViewModelProperty = DependencyProperty.Register(
            "IridiumWindowViewModel", typeof(IridiumWindowViewModel), typeof(IridiumWindow), new PropertyMetadata(default(IridiumWindowViewModel), OnIridiumWindowViewModelChanged));

        private static void OnIridiumWindowViewModelChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            ((IridiumWindow) d).DataContext = e.NewValue;
        }

        public IridiumWindowViewModel IridiumWindowViewModel
        {
            get => (IridiumWindowViewModel) GetValue(IridiumWindowViewModelProperty);
            set => SetValue(IridiumWindowViewModelProperty, value);
        }

        private BitmapSource _originalImage;

        public IridiumWindow()
        {
            InitializeComponent();
        }

        private void OnApplyOperationClick(object sender, RoutedEventArgs e)
        {
            if (sender is Button button && button.Content is OperationTemplate operationTemplate)
            {
                var vm = operationTemplate.OperationTemplateViewModel;
                var args = new OperationExecutionEventArgs(vm.Name, new object[] { IridiumWindowViewModel.Image });
                IridiumWindowViewModel.RaiseExecuteOperation(args);

                if (args.Result is BitmapSource img)
                {
                    IridiumWindowViewModel.Image = img;
                }
            }
        }

        private void OnOpenFile_Click(object sender, RoutedEventArgs e)
        {
            var dialog = new OpenFileDialog
            {
                CheckFileExists = true,
                Multiselect = false,
                Filter = "Image Files|*.png;*.jpg;*.jpeg;*.bmp;*.tif;*.tiff"
            };

            if (dialog.ShowDialog(this).GetValueOrDefault())
            {
                _originalImage = new BitmapImage(new Uri(dialog.FileName));
                IridiumWindowViewModel.Image = _originalImage;
            }
        }

        private void OnReset_Click(object sender, RoutedEventArgs e)
        {
            IridiumWindowViewModel.Image = _originalImage;
        }
    }
}
