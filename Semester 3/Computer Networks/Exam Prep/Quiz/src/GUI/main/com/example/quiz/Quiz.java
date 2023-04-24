package com.example.quiz;


import Interfaces.IQuestionsManager;
import Interfaces.IQuizManager;
import Managers.QuizManager;
import GUI.Controllers.QuizModeController;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Modality;
import javafx.stage.Stage;

public class Quiz {

    public void show(IQuestionsManager questionsManager, int noOfQuestions) throws Exception {
        FXMLLoader loader = new FXMLLoader(Quiz.class.getResource("QuizModeView.fxml"));
        Parent quizView = loader.load();
        QuizModeController controller = loader.getController();

        IQuizManager quizManager = new QuizManager(questionsManager.getRepository(), questionsManager.computeQuizQuestions(noOfQuestions));
        controller.setQuizManager(quizManager);

        Stage stage = new Stage();
        stage.initModality(Modality.APPLICATION_MODAL);
        stage.setTitle("Computer Networks Quiz");
        stage.setScene(new Scene(quizView));
        stage.showAndWait();
    }
}
