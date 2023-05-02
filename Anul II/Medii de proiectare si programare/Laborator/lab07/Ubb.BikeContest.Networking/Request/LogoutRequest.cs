using System;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Networking.Request.Request
{
    [Serializable]
    public class LogoutRequest : IRequest
    {
        private readonly User user;

        public LogoutRequest(User user)
        {
            this.user = user;
        }

        public virtual User User
        {
            get
            {
                return user;
            }
        }
    }

}