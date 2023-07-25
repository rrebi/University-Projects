<?php
session_start();

require_once 'db.php';

// Check if there is a notification message in the session
if (isset($_SESSION['notification'])) {
    $message = $_SESSION['notification'];

    // Clear the notification message from the session
    unset($_SESSION['notification']);
} else {
    $message = "";
}
?>


<!DOCTYPE html>
<html>
<head>
  <title>Index</title>
</head>
<body>
  <!-- Your content here -->
  <p>Get</p>

  <div style="display: flex; margin-top: 20px;">
    <a href="getAllP.php" style="margin-right: 10px;">Get All P</a>
    <a href="getAllPwC.php" style="margin-right: 10px;">Get All P where C=x</a>
    <a href="getAllC.php" style="margin-right: 10px;">Get All C</a>
    <a href="getPaginatedC.php" style="margin-right: 10px;">Get Paginated C</a>
    <a href="getPwSameC.php" style="margin-right: 10px;">Get family (parents)</a>
  </div>
  <br>

  <p>Add</p>
  <div style="display: flex; margin-top: 20px;">
    <a href="addP.php" style="margin-right: 10px;">Add P</a>
  </div>

  <br>
  <p>For this, you need to be logged in.</p>
  <div style="display: flex; margin-top: 20px;">
    <a href="getAllCwP.php" style="margin-right: 10px;">Get C for the logged in P</a>
    <a href="getLoggedPwSameC.php" style="margin-right: 10px;">Get family (parents)</a>
    <a href="addC.php" style="margin-right: 10px;">Add C</a>
    <a href="addCStringIsList.php" style="margin-right: 10px;">Add C with string is list</a>
    <a href="addExistingCtoP.php" style="margin-right: 10px;">Add Existing C to P</a>
    <a href="bulkAddC.php" style="margin-right: 10px;">Bulk add C</a>
    <a href="shoppingBasket.php">shoppingBasket</a>
  </div>

  <br>
  
  <!-- Display the notification message -->
  <div style="margin-top: 20px;">
    <?php echo $message; ?>
    <a href="login.php">Login</a>
    <a href="loginPwC.php">Login P w C</a>
    <a href="skipLogin.php">Logout</a>
  </div>

  <!-- Recently added children -->
  <h2>Recently Added Children</h2>
  <div id="content-container"></div>
  <button id="get-new-content">Get New Content</button>

  <!-- AJAX Script -->
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
  <script>
    $(document).ready(function() {
        $('#get-new-content').click(function() {
            var entryContainer = $('#content-container'); // Define entryContainer variable here

            $.ajax({
                url: 'get_new_content.php',
                success: function(data) {
                    data = JSON.parse(data);
                    console.log(data);

                    if (data.length > 0) {
                        data.forEach(function(child, index) { // Loop through each child and create an entry for them
                            var entry = `
                                <div style="display: none;">
                                    <h2>${child.child_name}</h2>
                                    <p>Parent ID: ${child.parent_id}</p>
                                    <p>Date: ${child.date}</p>
                                    <p>Number: ${child.number}</p>
                                </div>
                            `;

                            entryContainer.append(entry); // Add the entry to the container div and then fade it in
                            var childEntry = entryContainer.find('div').eq(index); // Get the child entry div at the current index
                            childEntry.delay(500 * index).fadeIn(500); // Adjust the fade duration as needed
                        });
                    } else {
                        entryContainer.html('<p>No recently added children found.</p>');
                    }
                }
            });
        });
    });
  </script>
</body>
</html>
