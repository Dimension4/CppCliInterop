using System;

namespace Iridium.Ui.Mvvm
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DependsOnAttribute : Attribute
    {
        public string[] Names { get; }

        public DependsOnAttribute(params string[] names)
        {
            Names = names;
        }
    }
}