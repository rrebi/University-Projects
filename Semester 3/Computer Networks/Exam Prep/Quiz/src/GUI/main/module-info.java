module com.example.quiz {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires org.kordamp.bootstrapfx.core;

    opens com.example.quiz to javafx.fxml;
    exports com.example.quiz;

    opens GUI.Controllers to javafx.fxml;
    exports GUI.Controllers;

    opens GUI.Messages to javafx.fxml;
    exports GUI.Messages;

    opens Interfaces to javafx.fxml;
    exports Interfaces;

    opens Managers to javafx.fxml;
    exports Managers;

    opens Models to javafx.fxml;
    exports Models;

    opens Repository to javafx.fxml;
    exports Repository;

    opens Utilities to javafx.fxml;
    exports Utilities;
}