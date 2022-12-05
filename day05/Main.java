import java.io.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {

    enum Part { ONE, TWO }
    
    public static void main(String[] args) throws IOException {

        String testFile = "input_05_test.txt";
        String actualFile = "input_05.txt";
        assert solve(testFile, Part.ONE).equals("CMZ");
        assert solve(testFile, Part.TWO).equals("MCD");

        String result = "";
        long t;
        
        t = System.nanoTime();
        result = solve(actualFile, Part.ONE);
        t = System.nanoTime() - t;
        System.out.println("part1 : " + result + " , " + t / 1000000.0 + " ms");
        
        t = System.nanoTime();
        result = solve(actualFile, Part.TWO);
        t = System.nanoTime() - t;
        System.out.println("part2 : " + result + " , " + t / 1000000.0 + " ms");
    }

    public static String solve(String filename, Part part) throws IOException {

        BufferedReader br = new BufferedReader(new FileReader(filename));
        String curLine = br.readLine();
        int numberOfStacks = (curLine.length() + 1) / 4;
        Stacks s = new Stacks(numberOfStacks);

        while (curLine != null) {
            for (int i = 0; i < s.numberOfStacks(); i++) {
                char c = curLine.charAt(4 * i + 1);
                if (c != ' ') s.addOnBottom(i, c);
            }
            curLine = br.readLine();
            if (curLine.startsWith(" 1 ")) {
                br.readLine();
                break;
            }
        }
        //System.out.println(s);

        Pattern p = Pattern.compile("[0-9]+");
        Matcher m;
        while ((curLine = br.readLine()) != null) {
            m = p.matcher(curLine);
            m.find(); int numberOfMoves = Integer.parseInt(m.group());
            m.find(); int srcStack = Integer.parseInt(m.group()) - 1;
            m.find(); int destStack = Integer.parseInt(m.group()) - 1;
            if (part == Part.ONE) {
                for (int i = 0; i < numberOfMoves; i++)
                    s.moveSrcTopToDest(srcStack, destStack);
            }
            else{
                char[] charactersToMove = new char[numberOfMoves];
                for (int i = 0; i < numberOfMoves; i++)
                    charactersToMove[numberOfMoves - 1 - i] = s.removeTop(srcStack);
                for (int i = 0; i < numberOfMoves; i++)
                    s.addOnTop(destStack, charactersToMove[i]);
            }
        }
        //System.out.println(s);
        
        br.close();
        return s.getStacksTops();
    }
}