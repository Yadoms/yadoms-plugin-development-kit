<?php
    if (isset($_POST["submit"])) {
        $pluginName = $_POST['pluginName'];
        $description = $_POST['description'];
        $author = $_POST['author'];
        $boost = $_POST['boost'];
        $poco = $_POST['poco'];
        $openssl = $_POST['openssl'];
        $yadoms = $_POST['yadoms'];
       
		include('pluginKitGenerator.php');
		if (!preg_match("/^[a-zA-Z0-9]+$/", $pluginName))  {
			echo "Incorrect pluginName input (only letters and digits allowed. Space, slash, dots and other special characters are not allowed)";
			return;
		}
	
		// If there are no errors, send the email
		if (!$errPluginName && !$errAuthor) {
			generate($pluginName, $description, $author, $boost, $poco, $openssl, $yadoms);
		}
    }
?>