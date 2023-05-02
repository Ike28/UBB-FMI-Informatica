using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ubb.BikeContest.Client.Controller
{
    public enum UserEvent
    {
        NEW_PARTICIPANT, RACES_MODIFIED
    };

    public class UserEventArgs : EventArgs
    {
        private readonly UserEvent userEvent;
        private readonly Object data;

        public UserEventArgs(UserEvent userEvent, object data)
        {
            this.userEvent = userEvent;
            this.data = data;
        }

        public UserEvent UserEventType
        {
            get { return userEvent; }
        }

        public object Data
        {
            get { return data; }
        }
    }
}
