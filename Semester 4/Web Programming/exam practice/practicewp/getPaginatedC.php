<?php
require_once 'db.php';

// Define the number of results per page
$resultsPerPage = 4;

// Get the current page number from the query parameters
$page = isset($_GET['page']) ? $_GET['page'] : 1;

// Calculate the starting index for the query
$startIndex = ($page - 1) * $resultsPerPage;


// Fetch children from the database with ordering and pagination
$stmt = $conn->prepare("SELECT *
                       FROM child 
                       LIMIT ?, ?");
$stmt->bind_param('ii', $startIndex, $resultsPerPage);
$stmt->execute();
$children = $stmt->get_result()->fetch_all(MYSQLI_ASSOC);

// Get the total number of children for pagination
$totalChildren = $conn->query("SELECT COUNT(*) as total FROM child")->fetch_assoc()['total'];

// Calculate the total number of pages
$totalPages = ceil($totalChildren / $resultsPerPage);

// Generate the URL for the next and previous page buttons
$nextPage = $page + 1;
$prevPage = $page - 1;
?>

<!DOCTYPE html>
<html>
<head>
  <title>All Children</title>
  <style>
    table {
      border-collapse: collapse; 
      width: 100%;
    }
    th, td {
      border: 1px solid black;
      padding: 8px;
      text-align: center;
    }
  </style>
  <script>
  // Client-side JavaScript to compute the most popular child string and display it
  function computeMostPopularChild() {
    var childStrings = [];

    // Retrieve stored child strings from localStorage
    var storedChildStrings = JSON.parse(localStorage.getItem('childStrings')) || [];

    // Add stored child strings to the array
    childStrings.push(...storedChildStrings);

    // Get the child strings from the current page
    var elements = document.getElementsByClassName('child-string');
    for (var i = 0; i < elements.length; i++) {
      var childString = elements[i].textContent;
      childStrings.push(childString);
    }

    // Store the updated child strings in localStorage
    localStorage.setItem('childStrings', JSON.stringify(childStrings));

    var counts = {};
    var maxCount = 0;
    var mostPopularChild = '';

    for (var i = 0; i < childStrings.length; i++) {
      var childString = childStrings[i];
      counts[childString] = (counts[childString] || 0) + 1;

      if (counts[childString] > maxCount) {
        maxCount = counts[childString];
        mostPopularChild = childString;
      }
    }

    // Create a new element to display the most popular child string
    var resultElement = document.createElement('p');
    resultElement.textContent = 'Most Popular Child String: ' + mostPopularChild;

    // Append the result element to the body
    document.body.appendChild(resultElement);
  }
</script>


</head>
<body>
  <h1>All Children Paginated</h1>
  <table>
    <tr>
      <th>ID</th>
      <th>idP</th>
      <th>String</th>
      <th>Date</th>
      <th>Number</th>
      <th>Actions</th>
    </tr>
    <?php foreach ($children as $child) { ?>
    <tr>
      <td><?php echo $child['id']; ?></td> 
      <td><?php echo $child['idP']; ?></td> 
      <td class="child-string"><?php echo $child['string']; ?></td>
      <td><?php echo $child['date']; ?></td>      
      <td><?php echo $child['number']; ?></td>
      <td>
        <a href="updateC.php?id=<?php echo $child['id']; ?>">Update</a> |
        <a href="deleteC.php?id=<?php echo $child['id']; ?>">Delete</a>
      </td>
    </tr>
    <?php } ?>
  </table>


  <div>
    <?php if ($page > 1) { ?>
      <a href="getPaginatedC.php?page=<?php echo $prevPage; ?>">Previous Page</a>
    <?php } ?>
    
    <?php if ($page < $totalPages) { ?>
      <a href="getPaginatedC.php?page=<?php echo $nextPage; ?>">Next Page</a>
    <?php } ?>
  </div>

  
  <button onclick="computeMostPopularChild()">Compute Most Popular Child</button>

</body>
</html>
