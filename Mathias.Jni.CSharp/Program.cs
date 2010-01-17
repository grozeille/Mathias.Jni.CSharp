using System;
using System.Collections.Generic;
using System.Text;
using MathiasJniCpp;

namespace Mathias.Jni.CSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            // on démarre la JVM avec mes bons arguments
            MathiasJniCpp.JVMWrapper.InitJvm(new String[] { "-Djava.class.path=Mathias.Jni.Java.jar" });

            // on créer un objet .Net qui wrappe l'objet Java
            // en C++/CLI, le destructeur des classes CLI sert de méthode "Dispose"
            using (MathiasJniCpp.MyJavaWrapper javaObject = new MathiasJniCpp.MyJavaWrapper())
            {
                // faire mumuse avec...
                javaObject.People = "Mathias";
                Console.WriteLine(javaObject.SayHello());
            }

            String mathias = "mathias";
            // test de perf avec un objet natif
            DateTime begin = DateTime.Now;
            for (int i = 0; i < 100000; i++)
            {
                MyCSharpClass obj = new MyCSharpClass();
                obj.People = mathias;
                obj.SayHello();
            }
            DateTime end = DateTime.Now;
            Console.WriteLine("c# object total time: {0}ms", end.Subtract(begin));

            // test de perf avec le wrapper vers l'objet Java
            begin = DateTime.Now;
            for (int i = 0; i < 100000; i++)
            {
                MyJavaWrapper obj = new MyJavaWrapper();
                obj.People = mathias;
                obj.SayHello();
            }
            end = DateTime.Now;
            Console.WriteLine("java object total time: {0}ms", end.Subtract(begin));
            

            // on libère la JVM
            JVMWrapper.ReleaseJvm();

            Console.WriteLine("Press a key to exit");
            Console.ReadKey(true);
        }
    }
}
