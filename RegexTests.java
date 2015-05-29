import static org.junit.Assert.*;

import java.util.HashSet;
import java.util.Set;

import org.junit.Before;
import org.junit.Test;


public class RegexTests {

    private static final int TIMEOUT = 500;
    
    private String text;
    private String starText;
    private Set<Answer> emptySet;
    
    @Before
    public void setup() {
        text = "foobarbazbinfoofoosuperduperfly";
        starText = "abc";
        emptySet = new HashSet<Answer>();
    }
    
    @Test (timeout = TIMEOUT, expected = IllegalArgumentException.class)
    public void testNullText() {
        Regex.find(null, "");
    }
    
    @Test (timeout = TIMEOUT, expected = IllegalArgumentException.class)
    public void testNullPattern() {
        Regex.find(text, null);
    }
    
    @Test (timeout = TIMEOUT)
    public void testEmptyText() {
        String pattern = "doesn't matter";
        assertEquals(emptySet, Regex.find("", pattern));
    }
    
    @Test (timeout = TIMEOUT, expected = IllegalArgumentException.class)
    public void testEmptyPattern() {
        Regex.find(text, "");
    }
    
    @Test (timeout = TIMEOUT)
    public void testStandardPatternNoMatch() {
        String pattern = "fos";
        assertEquals(emptySet, Regex.find(text, pattern));
    }
    
    @Test (timeout = TIMEOUT)
    public void testStandardPatternOneMatch() {
        String pattern = "bar";
        Set<Answer> ans = new HashSet<Answer>();
        ans.add(new Answer("bar", 3));
        assertEquals(ans, Regex.find(text, pattern));
    }
    
    @Test (timeout = TIMEOUT)
    public void testStandardPatternMultipleMatch() {
        String pattern = "foo";
        Set<Answer> ans = new HashSet<Answer>();
        ans.add(new Answer("foo", 0));
        ans.add(new Answer("foo", 12));
        ans.add(new Answer("foo", 15));
        assertEquals(ans, Regex.find(text, pattern)); //Tests multiple matches
    }
    
    @Test (timeout = TIMEOUT)
    public void testQuestionPatternNoMatch() {
        String pattern = "?fe";
        assertEquals(emptySet, Regex.find(text, pattern));
    }
    
    @Test (timeout = TIMEOUT)
    public void testQuestionPatternOneMatch() {
        String pattern = "b?n";
        Set<Answer> ans = new HashSet<Answer>();
        ans.add(new Answer("bin", 9));
        assertEquals(ans, Regex.find(text, pattern));
    }
    
    @Test (timeout = TIMEOUT)
    public void testQuestionPatternMultipleMatch() {
        String pattern = "?uper";
        Set<Answer> ans = new HashSet<Answer>();
        ans.add(new Answer("super", 18));
        ans.add(new Answer("duper", 23));
        assertEquals(ans, Regex.find(text, pattern));
    }
    
    @Test (timeout = TIMEOUT)
    public void testStarPatternSimple() {
        String pattern = "*";
        Set<Answer> ans = new HashSet<Answer>();
        ans.add(new Answer("a", 0));
        ans.add(new Answer("b", 1));
        ans.add(new Answer("c", 2));
        ans.add(new Answer("ab", 0));
        ans.add(new Answer("bc", 1));
        ans.add(new Answer("abc", 1));
        assertEquals(ans, Regex.find(starText, pattern));
    }
    
    @Test (timeout = TIMEOUT)
    public void testStarPatternNoMatch() {
        String pattern = "of*zb";
        assertEquals(emptySet, Regex.find(text, pattern));
    }
    
    @Test (timeout = TIMEOUT)
    public void testStarPatternOneMatch() {
        String pattern = "s*d";
        Set<Answer> ans = new HashSet<Answer>();
        ans.add(new Answer("superd", 18));
        assertEquals(ans, Regex.find(text, pattern));
    }
    
    @Test (timeout = TIMEOUT)
    public void testStarPatternMultipleMatch() {
        String pattern = "fo*b";
        Set<Answer> ans = new HashSet<Answer>();
        ans.add(new Answer("foob", 0));
        ans.add(new Answer("foobarb", 0));
        ans.add(new Answer("foobarbazb", 0));
        assertEquals(ans, Regex.find(text, pattern));
    }
    
    @Test (timeout = TIMEOUT)
    public void testDoubleStarPattern() {
        String pattern = "bi*fo*pe";
        Set<Answer> ans = new HashSet<Answer>();
        ans.add(new Answer("binfoofoosupe", 9));
        ans.add(new Answer("binfoofoosuperdupe", 9));
        assertEquals(ans, Regex.find(text, pattern));
    }
}