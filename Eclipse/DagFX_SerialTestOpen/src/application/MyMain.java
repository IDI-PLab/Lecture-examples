package application;
 
import java.io.IOException;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

 
public class MyMain extends Application {
    @Override
    public void start(Stage primaryStage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader();
        Parent root = (Parent) fxmlLoader.load(this.getClass().getResourceAsStream("Dag_FXML.fxml"));
        primaryStage.setScene(new Scene(root));
        primaryStage.show();
    }
       	
    public static void main(String[] args) {
        launch(args);
    }
}