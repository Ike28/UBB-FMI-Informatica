import java.io.File;
import java.util.Objects;

import static java.lang.Integer.signum;

public class Participant implements Comparable<Participant> {
    private Integer id;
    private Integer score;
    private Integer country;

    public Participant(Integer id, Integer score, Integer country) {
        this.id = id;
        this.score = score;
        this.country = country;
    }

    public static Participant fromString(String str, File file) {
        String[] data = str.split(",");
        Integer id = Integer.parseInt(data[0]);
        int score = Integer.parseInt(data[1]);
        int idx = file.getName().indexOf("_");
        // RezultateC1231_P3
        int country = Integer.parseInt(file.getName().substring(10, idx));
        return new Participant(id, score, country);
    }

    public Integer getId() {
        return id;
    }

    public Integer getScore() {
        return score;
    }

    public void setScore(Integer score) {
        this.score = score;
    }

    public Integer getCountry() {
        return country;
    }

    public void setCountry(Integer country) {
        this.country = country;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Participant that = (Participant) o;
        return Objects.equals(this.id, that.getId());
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.id);
    }

    @Override
    public int compareTo(Participant p) {
        int res = signum(this.score.compareTo(p.getScore()));
        if (res == 0)
            return signum(this.id.compareTo(p.getId()));

        return res;
    }

    @Override
    public String toString() {
        return "Participant{" +
                "id=" + id +
                ", score=" + score +
                ", country=" + country + 
                '}';
    }
}
