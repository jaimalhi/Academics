module ca.cmpt213.asn4.tictactoe {
    requires javafx.controls;
    requires javafx.fxml;

    exports ca.cmpt213.asn4.tictactoe.ui;
    opens ca.cmpt213.asn4.tictactoe.ui to javafx.fxml;
    exports ca.cmpt213.asn4.tictactoe.game;
    opens ca.cmpt213.asn4.tictactoe.game to javafx.fxml;
}