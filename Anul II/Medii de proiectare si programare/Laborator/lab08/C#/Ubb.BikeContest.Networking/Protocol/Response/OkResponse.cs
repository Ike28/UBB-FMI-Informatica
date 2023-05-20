using System;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Networking.Protocol.Response
{
    [Serializable]
    public class OkResponse : IResponse
    {
        private readonly User user;

        public OkResponse(User user)
        {
            this.user = user;
        }

        public User User { get { return user; } }
    }

}