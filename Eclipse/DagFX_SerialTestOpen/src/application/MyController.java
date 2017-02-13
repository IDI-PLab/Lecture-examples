package application;
import com.fazecast.jSerialComm.*;
import javafx.fxml.FXML;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.ListView;
import java.io.IOException;
import java.io.OutputStream;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

public class MyController {
	
	@FXML
    private TextField sendTextField;
	
	@FXML
    private TextArea textReceivedArea;
	
	@FXML
    private ListView<String> myListView;
	
	private SerialPort btPort;
	private SerialPort[] serialports;
	
	@FXML
	void initialize() {
		listSerialPorts();
	}
	
	@FXML
	void listSerialPorts() {
  	    serialports = SerialPort.getCommPorts();
    	String[] portNames = new String[serialports.length];
		int length = serialports.length;
		for(int i=0;i<length;i++) {
			portNames[i] = serialports[i].getDescriptivePortName();
		};
		ObservableList<String> items =FXCollections.observableArrayList (portNames);
		myListView.setItems(items);	
	}
	
	@FXML
	void openSelectedPort() {
		int index = myListView.getSelectionModel().getSelectedIndex(); 
		if (index > -1) {
		  btPort = serialports[index];
		  btPort.openPort();
		  btPort.addDataListener(new SerialPortDataListener() {
			   @Override
			   public int getListeningEvents() { return SerialPort.LISTENING_EVENT_DATA_AVAILABLE; }
			   @Override
			   public void serialEvent(SerialPortEvent event)
			   {
			      if (event.getEventType() != SerialPort.LISTENING_EVENT_DATA_AVAILABLE)
			         return;
			      byte[] newData = new byte[btPort.bytesAvailable()];
			      int numRead = btPort.readBytes(newData, newData.length);
			//      System.out.println("Read " + numRead + " bytes.");
			      String s = "";
			      for(int i=0;i<numRead;i++) {
						s += (char) newData[i];
			      };
			      textReceivedArea.appendText(s);
			   }
		  });
		}
	}
	
	@FXML
	void closePort() {
		btPort.closePort();
	}
	
	@FXML
	void sendText() {	
	    String s = sendTextField.getText() + "\r\n ";
		byte[] buffer = new byte[s.length()];
		for(int i=0;i<s.length();i++) {
			buffer[i] = (byte) s.charAt(i);
		};
		OutputStream out =  btPort.getOutputStream();
		try {
			out.write(buffer,0,s.length());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
	}
}
