module io.github.altoponix.plantsegmentation {
    requires javafx.controls;
    requires javafx.fxml;
    requires opencv;


    opens io.github.altoponix.plantsegmentation to javafx.fxml;
    exports io.github.altoponix.plantsegmentation;
}