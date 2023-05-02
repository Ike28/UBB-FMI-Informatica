using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Ubb.BikeContest.Model;
using Ubb.BikeContest.Model.data;

namespace Ubb.BikeContest.Services
{
    public interface IMainObserver
    {
        void ParticipantAdded(Participant participant);
        void RaceEntriesAdded(IEnumerable<RaceDto> races);
    }
}
