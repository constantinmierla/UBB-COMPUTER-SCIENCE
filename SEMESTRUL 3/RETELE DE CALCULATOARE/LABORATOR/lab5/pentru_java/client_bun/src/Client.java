import java.io.*;
import java.net.*;

public class Client {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("192.168.223.128", 1234);
            DataOutputStream out = new DataOutputStream(socket.getOutputStream());
            DataInputStream in = new DataInputStream(socket.getInputStream());

            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            System.out.print("Dimensiunea primului sir: ");
            int size1 = Integer.parseInt(reader.readLine());
            out.writeShort(size1);

            for (int i = 0; i < size1; i++) {
                System.out.print("Introduceți elementele pentru primul sir: ");
                out.writeShort(Short.parseShort(reader.readLine()));
            }

            System.out.print("Dimensiunea celui de-al doilea sir: ");
            int size2 = Integer.parseInt(reader.readLine());
            out.writeShort(size2);

            for (int i = 0; i < size2; i++) {
                System.out.print("Introduceți elementele pentru al doilea sir: ");
                out.writeShort(Short.parseShort(reader.readLine()));
            }


            int resultCount = in.readUnsignedShort();
            System.out.println("Elementele sunt : ");
            for (int i = 0; i < resultCount; i++) {
                int element = in.readUnsignedShort();
                System.out.println(element);
            }

            socket.close();
        } catch (EOFException e) {
            System.out.println("Conexiunea a fost închisă prematur.");
        } catch (SocketException e) {
            System.out.println("Eroare de socket: " + e.getMessage());
        } catch (IOException e) {
            e.printStackTrace();
        } catch (NumberFormatException e) {
            System.out.println("Eroare la conversia numerelor: " + e.getMessage());
        }
    }
}
