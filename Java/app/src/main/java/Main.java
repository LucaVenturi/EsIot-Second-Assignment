//import jssc.SerialPort;

import javax.swing.SwingUtilities;

public class Main {
    public static void main(String[] args) {
        String portName = "COM4";   // Cambia con la tua porta
        int baudRate = 9600;

        SwingUtilities.invokeLater(() -> {
            ArduinoControlGUI gui = new ArduinoControlGUI(portName, baudRate);
            gui.createAndShowGUI();
        });
    }
}