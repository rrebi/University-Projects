<?php
include 'db.php';
session_start();

$error_message = isset($_GET['error']) ? $_GET['error'] : '';

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $username = $_POST["username"];
    $string = $_POST["string"];

    $stmt = $conn->prepare("SELECT p.id, p.username, c.string FROM parent p INNER JOIN child c ON p.id = c.idP WHERE p.username = ? AND c.string = ?");
    $stmt->bind_param("ss", $username, $string);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($result->num_rows == 1) {
        $user = $result->fetch_assoc();
        $_SESSION["username"] = $user["username"];
        $_SESSION["parent_id"] = $user["id"];
        header("Location: index.php");
        exit();
    } else {
        $error_message = "Invalid username or string.";
    }
}
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
      <label for="string">String:</label>
      <input type="text" id="string" name="string" required>
      <br><br>
      <input type="submit" value="Login">
    </form>
    <form method="POST" action="skipLogin.php">
      <input type="submit" value="Skip Login">
    </form>
  </div>
</body>
</html>
