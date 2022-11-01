
// import java.io.BufferedReader;
import java.util.StringTokenizer;
import java.io.*;
import java.lang.StringBuilder;

public class ImageDecoding {

    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(
                    new InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }

        double nextDouble() {
            return Double.parseDouble(next());
        }

        String nextLine() {
            String str = "";
            try {
                str = br.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }
    }

    public static void main(String[] args) throws IOException {
        StringBuilder out = new StringBuilder();
        FastReader br = new FastReader();

        String separator = "";

        while (true) {
            // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            int r = Integer.parseInt(br.nextLine()); // number format exception because it reads a dot..
            // this time its a ". 10 10 10"

            if (r == 0) {
                break;
            }

            out.append(separator);

            String line;
            boolean error = false;

            int oldTotal = 0;
            for (int l = 0; l < r; l++) {

                line = br.nextLine();
                boolean filled = false;

                String[] bits = line.split(" ");
                int total = 0;
                for (int i = 0; i < bits.length; i++) {
                    if (i == 0) {
                        filled = bits[i].equals("#");
                    } else {

                        int x = Integer.parseInt(bits[i]);
                        total += x;
                        if (filled) {
                            // System.out.print("#".repeat(x));
                            out.append("#".repeat(x));
                        } else {
                            // System.out.print(".".repeat(x));
                            out.append(".".repeat(x));
                        }
                        filled = !filled;
                    }
                }
                // System.out.print("\n");
                out.append("\n");

                if (!error) {
                    if (oldTotal != 0) {
                        error = oldTotal != total;
                    } else {
                        oldTotal = total;
                    }

                }

            }
            if (error) {
                out.append("Error decoding image\n");
            }

            separator = "\n";
            

        }
        System.out.print(out.toString());

    }
}
