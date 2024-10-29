import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;

public class Client {

    public static void main(String[] args) {
        // Configurarea adresei IP și a portului serverului
        String serverAddress = "127.0.0.1"; // schimbă cu IP-ul serverului dacă este pe o altă mașină
        int port = 1234;

        try (Socket socket = new Socket(serverAddress, port);
             DataOutputStream out = new DataOutputStream(socket.getOutputStream());
             DataInputStream in = new DataInputStream(socket.getInputStream());
             Scanner scanner = new Scanner(System.in)) {

            // Citirea șirurilor de la utilizator
            System.out.print("Dimensiunea primului sir: ");
            int size1 = scanner.nextInt();
            int[] sir1 = new int[size1];
            System.out.println("Introduceți elementele pentru primul sir:");
            for (int i = 0; i < size1; i++) {
                sir1[i] = scanner.nextInt();
            }

            System.out.print("Dimensiunea celui de-al doilea sir: ");
            int size2 = scanner.nextInt();
            int[] sir2 = new int[size2];
            System.out.println("Introduceți elementele pentru al doilea sir:");
            for (int i = 0; i < size2; i++) {
                sir2[i] = scanner.nextInt();
            }

            // Trimiterea dimensiunilor și elementelor șirurilor către server
            out.writeShort(size1); // trimite dimensiunea primului sir
            for (int elem : sir1) {
                out.writeShort(elem); // trimite elementele din primul sir
            }

            out.writeShort(size2); // trimite dimensiunea celui de-al doilea sir
            for (int elem : sir2) {
                out.writeShort(elem); // trimite elementele din al doilea sir
            }

            // Primirea rezultatului de la server
            int resultSize = in.readUnsignedShort(); // primește dimensiunea rezultatului
            System.out.println("Elementele din primul sir care nu sunt în al doilea:");
            for (int i = 0; i < resultSize; i++) {
                int elem = in.readUnsignedShort();
                System.out.print(elem + " ");
            }
            System.out.println();

        } catch (IOException e) {
            System.err.println("Eroare de conectare la server: " + e.getMessage());
        }
    }
}
