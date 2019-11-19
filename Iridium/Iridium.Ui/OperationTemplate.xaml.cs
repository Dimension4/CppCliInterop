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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Iridium.Ui
{
    /// <summary>
    /// Interaction logic for OperationTemplate.xaml
    /// </summary>
    public partial class OperationTemplate : UserControl
    {
        public static readonly DependencyProperty OperationTemplateViewModelProperty = DependencyProperty.Register(
            "OperationTemplateViewModel", typeof(OperationTemplateViewModel), typeof(OperationTemplate),
            new PropertyMetadata(default(OperationTemplateViewModel), OnOperationTemplateViewModelChanged));

        private static void OnOperationTemplateViewModelChanged(DependencyObject d,
            DependencyPropertyChangedEventArgs e)
        {
            ((OperationTemplate) d).DataContext = e.NewValue;
        }

        public OperationTemplateViewModel OperationTemplateViewModel
        {
            get => (OperationTemplateViewModel) GetValue(OperationTemplateViewModelProperty);
            set => SetValue(OperationTemplateViewModelProperty, value);
        }

        public OperationTemplate()
        {
            InitializeComponent();
        }
    }
}