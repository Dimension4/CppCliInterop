using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace CSharp
{
    class Program
    {
        [DllImport("CppLib.dll")]
        private static extern void pluginMain();

        static void Main(string[] args)
        {
            pluginMain();
            
            Glue.Callbacks.SayHello();
            Glue.Callbacks.SayHello();
            Glue.Callbacks.SayHello();
            Console.WriteLine($"SomeBinaryFunction: {Glue.Callbacks.SomeBinaryFunction(1, 2)}");
            Console.WriteLine($"SomeBinaryFunction: {Glue.Callbacks.SomeBinaryFunction(10, 20)}");
            Console.WriteLine($"SomeBinaryFunction: {Glue.Callbacks.SomeBinaryFunction(100, 200)}");
            Glue.Callbacks.SomeUnaryFunction("This is a test!");
            Glue.Callbacks.SomeUnaryFunction("Wow!");

            Console.ReadKey();
        }
    }
}
