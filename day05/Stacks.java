import java.util.LinkedList;

public class Stacks {
    
    public final int numberOfStacks;
    private LinkedList<Character>[] stacks = null;

    public Stacks(int numberOfStacks){
        this.numberOfStacks = numberOfStacks;
        this.stacks = new LinkedList[this.numberOfStacks];
        for (int i = 0; i < this.numberOfStacks; i++)
            this.stacks[i] = new LinkedList<Character>();
    }

    public void addOnBottom(int i, char c){
        this.stacks[i].addFirst(c);
    }

    public void moveSrcTopToDest(int src, int dest){
        this.stacks[dest].addLast(stacks[src].pollLast());
    }

    public char removeTop(int i){
        return this.stacks[i].pollLast();
    }

    public void addOnTop(int i, char c){
        this.stacks[i].addLast(c);
    }

    public String getStacksTops(){
        String tops = "";
        for (int i = 0; i < this.numberOfStacks; i++)
            tops += stacks[i].peekLast();
        return tops;
    }

    @Override
    public String toString(){
         String s = "";
         for (int i = 0; i < this.numberOfStacks; i++)
             s += "Stack" + i + " : " + stacks[i] + "\n";
         return s;
    }
}
