package com.example.quiz;

import Interfaces.IQuizManager;
import GUI.Controllers.ResultController;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Modality;
import javafx.stage.Stage;

public class Result {

    public void show(IQuizManager quizManager) throws Exception {
        FXMLLoader loader = new FXMLLoader(Result.class.getResource("ResultView.fxml"));
        Parent resultView = loader.load();
        ResultController controller = loader.getController();

        controller.setQuizManager(quizManager);

        Stage stage = new Stage();
        stage.initModality(Modality.APPLICATION_MODAL);
        stage.setTitle("Computer Networks Quiz");
        stage.setScene(new Scene(resultView));
        stage.showAndWait();
    }
}
