<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
    <meta name="description" content="">
    <meta name="author" content="">

    <title>Yadoms Plugin Development Kit</title>

    <!-- Bootstrap core CSS -->
    <link href="../bootstrap-3.3.5-dist/css/bootstrap.min.css" rel="stylesheet">
    <link href="style.css" rel="stylesheet">

  </head>

  <body>
    <nav class="navbar navbar-inverse navbar-fixed-top">
      <div class="container">
        <div class="navbar-header">
          <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
            <span class="sr-only">Toggle navigation</span>
            <span class="icon-bar"></span>
          </button>
          <img src="../img/icon_256.png" class="img-responsive pull-left application-logo"/>
		  <a class="navbar-brand" href="#">Yadoms</a>
        </div>
          <ul class="nav navbar-nav">
            <li class="active"><a href="#">Presentation</a></li>
            <li><a href="https://github.com/Yadoms/yadoms/wiki/" target="blank">Wiki</a></li>
          </ul>
        </div><!--/.nav-collapse -->
      </div>
    </nav>
  
	<div class="container">
		<div class="row headerDoc">
			This page generate a basic pluginKit template.
			
		</div>
		
		<form  role="form" method="post" action="post.php">
		  <div class="form-group">
			<label for="inputPluginName">Plugin name</label>
			<input type="text" class="form-control" id="inputPluginName" name="pluginName" placeholder="pluginName" value="<?php echo htmlspecialchars($_POST['pluginName']); ?>">
			<?php echo "<p class='text-danger'>$errPluginName</p>";?>
		  </div>
		  <div class="form-group">
			<label for="inputDescription">Description</label>
			<textarea class="form-control" rows="3"  id="inputDescription" name="description" placeholder="description of the plugin"><?php echo htmlspecialchars($_POST['description']); ?></textarea>
		  </div>
		  <div class="form-group">
			<label for="inputAuthor">Author</label>
			<input type="text" class="form-control" id="inputAuthor" name="author" placeholder="your name" value="<?php echo htmlspecialchars($_POST['author']); ?>">
			<?php echo "<p class='text-danger'>$errAuthor</p>";?>
		  </div>

		  <hr/>
		  
		  <div class="form-group">
			<label for="inputBoost">Path to boost</label>
			<input type="text" class="form-control" id="inputBoost" name="boost" placeholder="path/to/boost_1_60_0">
			<label for="inputPoco">Path to Poco</label>
			<input type="text" class="form-control" id="inputPoco" name="poco" placeholder="path/to/poco-1.6.1-all">
			<label for="inputOpenssl">Path to OpenSSL</label>
			<input type="text" class="form-control" id="inputOpenssl" name="openssl" placeholder="path/to/openssl">
			<label for="inputYadoms">Path to Yadoms. If specified, the plugin project will ouput in the correct folder</label>
			<input type="text" class="form-control" id="inputYadoms" name="yadoms" placeholder="path/to/yadoms">
		  </div>
		  
			<div class="form-group">
				<input id="submit" name="submit" type="submit" value="Download" class="btn btn-primary">
			</div>		  
		  
			<div class="form-group">
				<?php echo $result; ?>    
			</div>
	
		</form>
	</div>
  
    <!-- Bootstrap core JavaScript
    ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <script src="../js/jquery.min.js"></script>
	<script src="../bootstrap-3.3.5-dist/js/bootstrap.min.js"></script>  
  </body>
</html>
