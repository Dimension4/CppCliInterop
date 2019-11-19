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
      
        public IridiumWindow()
        {
            InitializeComponent();
        }
    }
}
