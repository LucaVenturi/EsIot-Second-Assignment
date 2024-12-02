import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ArduinoControlGUI {

    private SerialCommChannel channel;

    public ArduinoControlGUI(String portName, int baudRate) {
        try {
            // Inizializzazione del canale seriale
            channel = new SerialCommChannel(portName, baudRate);
            System.out.println("Connected to " + portName);
        } catch (Exception ex) {
            ex.printStackTrace();
            JOptionPane.showMessageDialog(null, "Errore nella connessione seriale: " + ex.getMessage(),
                    "Errore", JOptionPane.ERROR_MESSAGE);
            System.exit(1);
        }
    }

    public void createAndShowGUI() {
        JFrame frame = new JFrame("Arduino Control");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 150);
        frame.setLayout(new GridLayout(2, 1));

        // Bottone per svuotare il contenitore
        JButton emptyButton = new JButton("Svuota Contenitore");
        emptyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                sendCommand("EMPTY");
            }
        });

        // Bottone per resettare
        JButton resetButton = new JButton("Reset Temperatura");
        resetButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                sendCommand("RESTORE");
            }
        });

        frame.add(emptyButton);
        frame.add(resetButton);

        frame.setVisible(true);
    }

    private void sendCommand(String command) {
        try {
            channel.sendMsg(command);
            System.out.println("Comando inviato: " + command);
        } catch (Exception ex) {
            ex.printStackTrace();
            JOptionPane.showMessageDialog(null, "Errore durante l'invio del comando: " + ex.getMessage(),
                    "Errore", JOptionPane.ERROR_MESSAGE);
        }
    }
}