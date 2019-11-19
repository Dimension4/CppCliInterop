using System;

namespace Iridium.Ui.Mvvm
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct | AttributeTargets.Property)]
    public class SelfManagedAttribute : Attribute
    {
    }
}