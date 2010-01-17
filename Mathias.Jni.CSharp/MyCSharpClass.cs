using System;
using System.Collections.Generic;
using System.Text;

namespace Mathias.Jni.CSharp
{
    /// <summary>
    /// la même classe de test, mais en pure .net
    /// </summary>
    public class MyCSharpClass
    {
        private String people;

        public String People
        {
            get { return people; }
            set { people = value; }
        }

        public String SayHello()
        {
            return String.Format("Hello {0} from .Net!", people);
        }
    }
}
