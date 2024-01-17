import java.util.Objects;

public class CheckClass {
    private Integer counter;
    private Integer goal;

    public CheckClass(Integer goal) {
        this.counter = 0;
        this.goal = goal;
    }

    public synchronized void increment() {
        counter++;
    }

    public synchronized boolean finished() {
        return Objects.equals(counter, goal);
    }
}
