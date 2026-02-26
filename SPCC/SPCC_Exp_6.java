import java.util.*;

public class SPCC_Exp_6 {

    // Check if any removed temp exists inside expression
    static String[] tempF(String code, Map<String, String> removed) {
        for (Map.Entry<String, String> entry : removed.entrySet()) {
            String k = entry.getKey();
            String v = entry.getValue();
            if (code.contains(k)) {
                return new String[]{k, v};
            }
        }
        return new String[]{};
    }

    static Map<String, String> solve(List<String> data) {
        Map<String, String> temp = new LinkedHashMap<>();
        Map<String, String> removed = new HashMap<>();

        for (String line : data) {
            int index = line.indexOf('=');
            String name = line.substring(0, index).trim();
            String code = line.substring(index + 1).trim();

            String[] t = tempF(code, removed);
            if (t.length != 0) {
                code = code.replace(t[0], t[1]);
            }

            if (!temp.containsValue(code)) {
                temp.put(name, code);
            } else {
                String key = "";
                for (Map.Entry<String, String> entry : temp.entrySet()) {
                    if (entry.getValue().equals(code)) {
                        key = entry.getKey();
                        break;
                    }
                }
                removed.put(name, key);
            }
        }
        return temp;
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of TAC statements: ");
        int n = sc.nextInt();
        sc.nextLine(); // consume newline

        List<String> data = new ArrayList<>();
        System.out.println("Enter TAC statements (one per line, e.g., t1=a+b):");
        for (int i = 0; i < n; i++) {
            data.add(sc.nextLine());
        }

        Map<String, String> ans = solve(data);

        int count = 1;
        Map<String, String> updated = new LinkedHashMap<>(ans);

        System.out.println("\nOptimized TAC:");
        for (Map.Entry<String, String> entry : ans.entrySet()) {
            String oldTemp = entry.getKey();
            String newTemp = "t" + count;

            System.out.print(newTemp + " = ");

            for (Map.Entry<String, String> e : updated.entrySet()) {
                updated.put(e.getKey(),
                        updated.get(e.getKey()).replace(oldTemp, newTemp));
            }

            System.out.println(updated.get(oldTemp));
            count++;
        }

        sc.close();
    }
}