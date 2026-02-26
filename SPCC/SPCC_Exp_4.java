import java.util.*;

public class SPCC_Exp_4 {

    static Map<String, List<String>> productions = new LinkedHashMap<>();
    static Map<String, Set<String>> first = new LinkedHashMap<>();
    static Map<String, Set<String>> follow = new LinkedHashMap<>();
    static Set<String> nonTerminals = new LinkedHashSet<>();
    static Set<String> terminals = new LinkedHashSet<>();

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of productions: ");
        int n = sc.nextInt();
        sc.nextLine();

        for (int i = 0; i < n; i++) {
            System.out.print("Enter production: ");
            String input = sc.nextLine();

            String[] parts = input.split("=");
            String lhs = parts[0].trim();
            String[] rhs = parts[1].split("\\|");

            nonTerminals.add(lhs);
            productions.putIfAbsent(lhs, new ArrayList<>());

            for (String r : rhs) {
                productions.get(lhs).add(r.trim());
            }
        }

        findTerminals();
        computeFirst();
        computeFollow();

        printFirst();
        printFollow();

        if (checkLL1()) {
            System.out.println("\nGrammar is LL(1)");
        } else {
            System.out.println("\nGrammar is NOT LL(1)");
        }
    }

    // ---------------- FIND TERMINALS ----------------
    static void findTerminals() {

        for (List<String> rhsList : productions.values()) {
            for (String rhs : rhsList) {

                for (char ch : rhs.toCharArray()) {
                    String s = String.valueOf(ch);

                    if (!nonTerminals.contains(s) && !s.equals("#")) {
                        terminals.add(s);
                    }
                }
            }
        }
    }

    // ---------------- COMPUTE FIRST ----------------
    static void computeFirst() {

        for (String nt : nonTerminals) {
            first.put(nt, new HashSet<>());
        }

        boolean changed;

        do {
            changed = false;

            for (String nt : productions.keySet()) {

                for (String rhs : productions.get(nt)) {

                    for (int i = 0; i < rhs.length(); i++) {

                        String symbol = String.valueOf(rhs.charAt(i));

                        if (!nonTerminals.contains(symbol)) {

                            if (first.get(nt).add(symbol))
                                changed = true;

                            break;

                        } else {

                            Set<String> firstSet = first.get(symbol);

                            for (String f : firstSet) {

                                if (!f.equals("#"))
                                    if (first.get(nt).add(f))
                                        changed = true;
                            }

                            if (!firstSet.contains("#"))
                                break;
                        }

                        if (i == rhs.length() - 1) {
                            if (first.get(nt).add("#"))
                                changed = true;
                        }
                    }
                }
            }

        } while (changed);
    }

    // ---------------- COMPUTE FOLLOW ----------------
    static void computeFollow() {

        for (String nt : nonTerminals) {
            follow.put(nt, new HashSet<>());
        }

        // Start symbol gets $
        String startSymbol = productions.keySet().iterator().next();
        follow.get(startSymbol).add("$");

        boolean changed;

        do {
            changed = false;

            for (String nt : productions.keySet()) {

                for (String rhs : productions.get(nt)) {

                    for (int i = 0; i < rhs.length(); i++) {

                        String symbol = String.valueOf(rhs.charAt(i));

                        if (nonTerminals.contains(symbol)) {

                            int oldSize = follow.get(symbol).size();

                            if (i + 1 < rhs.length()) {

                                String next = String.valueOf(rhs.charAt(i + 1));

                                if (!nonTerminals.contains(next)) {

                                    follow.get(symbol).add(next);

                                } else {

                                    follow.get(symbol).addAll(first.get(next));
                                    follow.get(symbol).remove("#");

                                    if (first.get(next).contains("#")) {
                                        follow.get(symbol).addAll(follow.get(nt));
                                    }
                                }

                            } else {
                                follow.get(symbol).addAll(follow.get(nt));
                            }

                            if (follow.get(symbol).size() > oldSize)
                                changed = true;
                        }
                    }
                }
            }

        } while (changed);
    }

    // ---------------- GET FIRST OF STRING ----------------
    static Set<String> getFirstOfString(String str) {

        Set<String> result = new HashSet<>();

        for (int i = 0; i < str.length(); i++) {

            String symbol = String.valueOf(str.charAt(i));

            if (!nonTerminals.contains(symbol)) {
                result.add(symbol);
                return result;
            }

            result.addAll(first.get(symbol));
            result.remove("#");

            if (!first.get(symbol).contains("#"))
                return result;

            if (i == str.length() - 1)
                result.add("#");
        }

        return result;
    }

    // ---------------- BUILD + PRINT PARSING TABLE ----------------
    static boolean checkLL1() {

        Map<String, Map<String, String>> table = new LinkedHashMap<>();

        for (String nt : productions.keySet()) {
            table.put(nt, new LinkedHashMap<>());
        }

        boolean isLL1 = true;

        for (String nt : productions.keySet()) {

            for (String rhs : productions.get(nt)) {

                Set<String> firstSet = getFirstOfString(rhs);

                // Add FIRST entries
                for (String terminal : firstSet) {

                    if (!terminal.equals("#")) {

                        if (table.get(nt).containsKey(terminal)) {
                            isLL1 = false;   // conflict
                        } else {
                            table.get(nt).put(terminal, rhs);
                        }
                    }
                }

                // If epsilon present → use FOLLOW
                if (firstSet.contains("#")) {

                    for (String f : follow.get(nt)) {

                        if (table.get(nt).containsKey(f)) {
                            isLL1 = false;
                        } else {
                            table.get(nt).put(f, rhs);
                        }
                    }
                }
            }
        }

        // -------- PRINT TABLE --------
        System.out.println("\nLL(1) Parsing Table:");

        List<String> termList = new ArrayList<>(terminals);
        termList.add("$");

        System.out.print("NT/T\t");
        for (String t : termList) {
            System.out.print(t + "\t");
        }
        System.out.println();

        for (String nt : productions.keySet()) {

            System.out.print(nt + "\t");

            for (String t : termList) {

                if (table.get(nt).containsKey(t)) {
                    System.out.print(nt + "=" + table.get(nt).get(t) + "\t");
                } else {
                    System.out.print("-\t");
                }
            }

            System.out.println();
        }

        return isLL1;
    }

    // ---------------- PRINT FIRST ----------------
    static void printFirst() {

        System.out.println("\nFIRST Sets:");

        for (String nt : first.keySet()) {
            System.out.println(nt + " = " + first.get(nt));
        }
    }

    // ---------------- PRINT FOLLOW ----------------
    static void printFollow() {

        System.out.println("\nFOLLOW Sets:");

        for (String nt : follow.keySet()) {
            System.out.println(nt + " = " + follow.get(nt));
        }
    }
}