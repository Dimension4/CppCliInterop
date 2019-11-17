using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using Glue;

namespace CSharp
{
    class Program
    {
        [DllImport("CppLib.dll")]
        private static extern void pluginMain();

        static void Main(string[] args)
        {
            pluginMain();

            ManagedApi.SayHello();

            ManagedApi.Greet("Peter Griffin");

            Console.WriteLine($"Add(1, 1): {ManagedApi.Add(1, 1)}");
            Console.WriteLine($"Add(10, 4): {ManagedApi.Add(10, 4)}");

            Console.WriteLine($"Accumulating: {ManagedApi.Accumulate(1)}");
            Console.WriteLine($"Accumulating: {ManagedApi.Accumulate(1)}");
            Console.WriteLine($"Accumulating: {ManagedApi.Accumulate(1)}");

            ManagedApi.SayGoodbye();

            Console.ReadKey();
        }
    }
}
