
public class Answer {

    private String substring;
    private int index;
    
    public Answer(String substring, int index) {
        this.substring = substring;
        this.index = index;
    }
    
    public String getSubstring() {
        return substring;
    }
    
    public int getIndex() {
        return index;
    }
    
    public boolean equals(Object other) {
        if (other == null || !(other instanceof Answer)) {
            return false;
        }
        if (other == this) {
            return true;
        }
        Answer o = (Answer) other;
        if (substring.equals(o.getSubstring())) {
            if (index == o.getIndex()) {
                return true;
            }
        }
        return false;
    }
    
    public int hashCode() {
        int result = 17;
        result = 31 * result + substring.hashCode();
        result = 31 * result + index;
        return result;
    }
    
    public String toString() {
        return index + "\t" + substring;
    }
}