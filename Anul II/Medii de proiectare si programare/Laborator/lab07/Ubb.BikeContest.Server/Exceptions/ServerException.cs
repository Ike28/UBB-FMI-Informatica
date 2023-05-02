using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ubb.BikeContest.Services.Exceptions
{
    public class ServerException : Exception
    {
        public ServerException() : base() { }

        public ServerException(string msg) : base(msg) { }

        public ServerException(string msg, Exception ex) : base(msg, ex) { }

    }
}
