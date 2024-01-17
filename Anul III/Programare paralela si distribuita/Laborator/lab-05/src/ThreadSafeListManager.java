import java.util.Set;

public class ThreadSafeListManager {
    private Set<Participant> synchronizedBlackListSet;
    private ThreadSafeLinkedList<Participant> lst;

    public ThreadSafeListManager(ThreadSafeLinkedList<Participant> lst, Set<Participant> synchronizedBlackListSet) {
        this.synchronizedBlackListSet = synchronizedBlackListSet;
        this.lst = lst;
    }

    public ThreadSafeLinkedList<Participant> getLst() {
        return lst;
    }

    public void processParticipant(Participant participant) {
        Node<Participant> prev = lst.search(participant);
        //System.out.println(prev);
        if (prev == null) {
            if (participant.getScore() > -1 && !synchronizedBlackListSet.contains(participant)) {
                lst.add(participant);
            } else {
                synchronizedBlackListSet.add(participant);
            }
        } else {
            if (participant.getScore() == -1) {
                lst.delete(prev);
                synchronizedBlackListSet.add(participant);
            } else {
                participant.setScore(participant.getScore() + prev.getNext().getData().getScore());
                lst.update(prev, participant);
            }
        }
    }

    public void sortList() {
        lst.sort();
    }
}
