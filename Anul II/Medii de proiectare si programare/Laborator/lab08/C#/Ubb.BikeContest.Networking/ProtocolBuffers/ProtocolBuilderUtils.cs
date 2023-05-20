using Com.Ubb.Protocolbuffers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;

using ProtocolUser = Com.Ubb.Protocolbuffers.User;
using User = Ubb.BikeContest.Model.User;

namespace Ubb.BikeContest.Networking.ProtocolBuffers
{
    static class ProtocolBuilderUtils
    {
        public static BikeContestRequest CreateLoginRequest(string username, string passwordToken)
        {
            return new BikeContestRequest
            {
                Type = BikeContestRequest.Types.Type.Login,
                Username = username,
                PasswordToken = passwordToken
            };
        }

        public static BikeContestRequest CreateLogoutRequest(User user)
        {
            ProtocolUser result = new ProtocolUser
            {
                Id = user.Id,
                Username = user.Username,
                FullName = user.FullName,
                PasswordToken = user.Password
            };

            return new BikeContestRequest
            {
                Type = BikeContestRequest.Types.Type.Logout,
                User = result
            };
        }

        public static BikeContestResponse CreateOkResponse()
        {
            return new BikeContestResponse
            {
                Type = BikeContestResponse.Types.Type.Ok
            };
        }

        public static BikeContestResponse CreateOkResponse(User user)
        {
            ProtocolUser result = new ProtocolUser
            {
                Id = user.Id,
                Username = user.Username,
                FullName = user.FullName,
                PasswordToken = user.Password
            };

            return new BikeContestResponse
            {
                Type = BikeContestResponse.Types.Type.Ok,
                User = result
            };
        }

        public static BikeContestResponse CreateErrorResponse(string message)
        {
            return new BikeContestResponse
            {
                Type = BikeContestResponse.Types.Type.Error,
                ErrorMessage = message
            };
        }

        public static string GetErrorMessage(BikeContestResponse response)
        {
            return response.ErrorMessage;
        }

        public static User GetUser(BikeContestRequest request)
        {
            ProtocolUser user = request.User;
            User result = new(user.Username, user.FullName, user.PasswordToken)
            {
                Id = user.Id
            };
            return result;
        }

        public static User GetUser(BikeContestResponse request)
        {
            ProtocolUser user = request.User;
            User result = new(user.Username, user.FullName, user.PasswordToken)
            {
                Id = user.Id
            };
            return result;
        }

        public static string GetUsername(BikeContestRequest request)
        {
            return request.Username;
        }

        public static string GetPasswordToken(BikeContestRequest request)
        {
            return request.PasswordToken;
        }
    }
}
