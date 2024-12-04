import javax.swing.*;
import java.awt.*;

public class ArduinoControlGUI {

    private SerialCommChannel channel;
    private JLabel temperatureLabel;
    private JLabel levelLabel;

    public ArduinoControlGUI(String portName, int baudRate) {
        try {
            // Inizializzazione del canale seriale
            channel = new SerialCommChannel(portName, baudRate);
            System.out.println("Connected to " + portName);
        } catch (Exception ex) {
            ex.printStackTrace();
            JOptionPane.showMessageDialog(null, "Errore nella connessione seriale: " + ex.getMessage(), "Errore", JOptionPane.ERROR_MESSAGE);
            System.exit(1);
        }
    }

    public void createAndShowGUI() {
        JFrame frame = new JFrame("Arduino Control");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);
        frame.setLayout(new BorderLayout());

        // Pannello superiore per le etichette
        JPanel topPanel = new JPanel(new GridLayout(2, 2));
        topPanel.setBorder(BorderFactory.createTitledBorder("Stato Attuale"));

        JLabel tempTitleLabel = new JLabel("Temperatura:");
        temperatureLabel = new JLabel("N/A");
        JLabel levelTitleLabel = new JLabel("Livello:");
        levelLabel = new JLabel("N/A");

        topPanel.add(tempTitleLabel);
        topPanel.add(temperatureLabel);
        topPanel.add(levelTitleLabel);
        topPanel.add(levelLabel);

        // Pannello inferiore per i pulsanti
        JPanel bottomPanel = new JPanel(new GridLayout(1, 2));
        bottomPanel.setBorder(BorderFactory.createTitledBorder("Controlli"));

        JButton emptyButton = new JButton("Svuota Contenitore");
        emptyButton.addActionListener(e -> sendCommand("EMPTY"));

        JButton resetButton = new JButton("Reset Temperatura");
        resetButton.addActionListener(e -> sendCommand("RESTORE"));

        bottomPanel.add(emptyButton);
        bottomPanel.add(resetButton);

        // Aggiungere i pannelli al frame
        frame.add(topPanel, BorderLayout.CENTER);
        frame.add(bottomPanel, BorderLayout.SOUTH);

        frame.setVisible(true);

        // Iniziare un thread per aggiornare le etichette
        new Thread(this::updateLabels).start();
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

    private void updateLabels() {
        try {
            while (true) {
                if (channel.isMsgAvailable()) {
                    String msg = channel.receiveMsg();
                    System.out.println("Messaggio ricevuto: " + msg);

                    // Esempio di parsing del messaggio
                    if (msg.startsWith("TEMP: ")) {
                        String temp = msg.substring(6);
                        SwingUtilities.invokeLater(() -> temperatureLabel.setText(temp + " °C"));
                    } else if (msg.startsWith("LEVEL: ")) {
                        String level = msg.substring(7);
                        SwingUtilities.invokeLater(() -> levelLabel.setText(level + " %"));
                    }
                }
                Thread.sleep(100); // eseguita ogni 100ms (come lo scheduler arduino)
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}
