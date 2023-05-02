using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ubb.BikeContest.Services.src.Exceptions;

public class ContestDataException : Exception
{
    public ContestDataException() : base() { }

    public ContestDataException(string msg) : base(msg) { }

    public ContestDataException(string msg, Exception ex) : base(msg, ex) { }

}
