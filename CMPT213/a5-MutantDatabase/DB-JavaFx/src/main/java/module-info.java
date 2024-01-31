module ca.cmpt213.asn5.mutantdb {
    requires javafx.controls;
    requires javafx.fxml;
    requires com.google.gson;

    exports ca.cmpt213.asn5.mutantdb;
    opens ca.cmpt213.asn5.mutantdb to javafx.fxml;
    exports ca.cmpt213.asn5.mutantdb.btnhandler;
    opens ca.cmpt213.asn5.mutantdb.btnhandler to com.google.gson;
}