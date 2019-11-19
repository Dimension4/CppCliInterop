using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Navigation;

namespace Iridium.Ui.Tests
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            MainWindow = new IridiumWindow
            {
                IridiumWindowViewModel = new IridiumWindowViewModel
                {
                    OperationTemplates =
                    {
                        new OperationTemplateViewModel
                        {
                            Name = "Convolve",
                            Description = "Applies a convolution kernel to the image.",
                            Parameters = new ReadOnlyObservableCollection<ParameterInfo>(
                                new ObservableCollection<ParameterInfo>
                                {
                                    new ParameterInfo("width", typeof(int)),
                                    new ParameterInfo("height", typeof(int)),
                                    new ParameterInfo("kernel", typeof(float[,]))
                                })
                        },
                        new OperationTemplateViewModel
                        {
                            Name = "Erode",
                            Description = "Applies an erosion to the image.",
                            Parameters = new ReadOnlyObservableCollection<ParameterInfo>(
                                new ObservableCollection<ParameterInfo> {new ParameterInfo("size", typeof(int))})
                        },
                        new OperationTemplateViewModel
                        {
                            Name = "Dilate",
                            Description = "Applies a dilation to the image.",
                            Parameters = new ReadOnlyObservableCollection<ParameterInfo>(
                                new ObservableCollection<ParameterInfo> {new ParameterInfo("size", typeof(int))})
                        },
                        new OperationTemplateViewModel
                        {
                            Name = "Invert",
                            Description = "Inverts the image"
                        },
                        new OperationTemplateViewModel
                        {
                            Name = "Rotate",
                            Description = "Rotates the image",
                            Parameters = new ReadOnlyObservableCollection<ParameterInfo>(
                                new ObservableCollection<ParameterInfo> {new ParameterInfo("angle", typeof(float))})
                        }
                    }
                }
            };

            MainWindow.Show();
            base.OnStartup(e);
        }
    }
}