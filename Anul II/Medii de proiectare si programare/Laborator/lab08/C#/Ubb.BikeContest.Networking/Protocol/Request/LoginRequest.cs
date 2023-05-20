using System;

namespace Ubb.BikeContest.Networking.Protocol.Request
{

    [Serializable]
    public class LoginRequest : IRequest
    {
        private readonly string username;
        private readonly string passwordToken;

        public LoginRequest(string username, string passwordToken)
        {
            this.username = username;
            this.passwordToken = passwordToken;
        }

        public virtual string Username
        {
            get { return username; }
        }

        public virtual string Token
        {
            get { return passwordToken; }
        }
    }

}