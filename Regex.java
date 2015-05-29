import java.util.HashSet;
import java.util.Set;


public class Regex {
    
    public static Set<Answer> find(String text, String pattern) {
        if (text == null || pattern == null) {
            throw new IllegalArgumentException("Error. Null argument.");
        }
        if (pattern.length() == 0) {
            throw new IllegalArgumentException("Error. Empty pattern.");
        }
        Set<Answer> result = new HashSet<Answer>();
        if (text.length() > 0) {
            match(text, pattern, result, -1, 0, 0, "");
        }
        return result;
    }
    
    private static void match(String text, String pattern, Set<Answer> result,
            int orig, int currT, int currP, String s) {
        int curr = currT;
        int tPoint = curr;
        int pPoint = currP;
        String sub = s;
        while (curr <= text.length() - pattern.length() + pPoint - 1) {
            tPoint = curr;
            pPoint = currP;
            if (orig != -1) {
                sub = s + text.substring(currT, curr);
            } else {
                sub = s;
            }
            while (pPoint < pattern.length()
                    && (text.charAt(tPoint) == pattern.charAt(pPoint)
                    || pattern.charAt(pPoint) == '?'
                    || pattern.charAt(pPoint) == '*')) {
                sub += text.charAt(tPoint);
                tPoint += 1;
                pPoint += 1;
                if (pattern.charAt(pPoint - 1) == '*') {
                    if (pPoint >= pattern.length()) {
                        String temp = sub;
                        for (int i = tPoint; i < text.length(); i += 1) {
                            temp += text.charAt(i);
                            if (orig != -1) {
                                result.add(new Answer(temp, orig));
                            } else {
                                result.add(new Answer(temp, curr));
                            }
                        }
                    } else {
                        if (orig == -1) {
                            match(text, pattern, result, curr, tPoint, pPoint, sub);
                        } else {
                            match(text, pattern, result, orig, tPoint, pPoint, sub);
                        }
                    }
                }
            }
            if (pPoint >= pattern.length()) {
                if (orig != -1) {
                    result.add(new Answer(sub, orig));
                } else {
                    result.add(new Answer(sub, curr));
                }
            }
            curr += 1;
        }
    }
    
    public static void main(String[] args) {
        Set<Answer> s = Regex.find("foobarbazbinfoofoosuperduperfly", "bi*fo*pe");
        for (Answer ans : s) {
            System.out.println(ans);
        }
    }
}