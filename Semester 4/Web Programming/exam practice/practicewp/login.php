<?php
include 'db.php';
session_start();

$error_message = isset($_GET['error']) ? $_GET['error'] : '';

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $username = $_POST["username"];
    $password = $_POST["password"];


    $stmt = $conn->prepare("SELECT id, username FROM parent WHERE username = ? AND password = ?");
    $stmt->bind_param("ss", $username, $password);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($result->num_rows == 1) {
        $user = $result->fetch_assoc();
        $_SESSION["username"] =  $user["username"];
        $_SESSION["parent_id"] = $user["id"];
        header("Location: index.php");
        exit();
    } else {
        echo "Invalid username or password.";
    }

}

//By incorporating JavaScript, you can add client-side validation, manipulate the DOM, make AJAX requests, and perform various other tasks to enhance interactivity on the client-side of your application.





?>



<!DOCTYPE html>
<html>
<head>
  <title>Login</title>
  </head>
<body>
  <div class="login-container">
    <h1>Login</h1>
    <?php if (!empty($error_message)) { ?>
    <p><?php echo $error_message; ?></p>
    <?php } ?>
    <form method="POST" action="">
      <label for="username">Username:</label>
      <input type="text" id="username" name="username" required>
      <br>
      <label for="password">Password:</label>
      <input type="password" id="password" name="password" required>
      <br>
      <input type="submit" value="Login">
    </form>
    <form method="POST" action="skipLogin.php">
      <input type="submit" value="Skip Login">
    </form>
  </div>
</body>
</html>


