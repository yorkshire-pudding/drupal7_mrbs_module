// $Id: README.txt,v 1.1 2009/02/14 16:18:32 wesku Exp $

Drupal - MRBS integration

This very simple module offers single sign-on integration with MRBS ( http://mrbs.sourceforge.net/ ) and Drupal. The module uses Drupal user accounts and permissions with MRBS. Currently the module has only been tested when installed directly in a subdirectory on Drupal root directory, but it should be quite easy to modify it for other installations.

Installation
- Install MRBS in a subdirectory on your Drupal installation
- Install Drupal module and enable it
- Copy auth_drupal.inc from mrbs_inc subdirectory to your mrbs install directory
- Change config.inc.php:
  - $auth["type"] = "drupal";
- Add your Drupal settings in config.inc.php (the same as Drupal settings.php) not MRBS settings
  - $auth['drupal']['db_system'] = 'drupal_db_system';
  - $auth['drupal']['db_host'] = 'drupal_db_host';
  - $auth['drupal']['db_username'] = 'drupal_db_username';
  - $auth['drupal']['db_password'] = 'drupal_db_password';
  - $auth['drupal']['db_name'] = 'drupal_db_name';

That's it, MRBS users and should now be managed by Drupal.

OPTIONAL
----------
- Copy session_drupal.inc from mrbs_inc subdirectory to your mrbs install directory
- Change config.inc.php:
  - $auth["session"] = "drupal";
- Enable Drupal Menu Token Module.
- Set [current-user:name] as a token of the menu that links to MRBS in Drupal to send the name of the user as a user GET variable.
- Links to MRBS admin.php passing the current user name as the user GET variable (for example your_drupal_site/mrbs/web/admin.php?user=[current-user:name]).

The user log in MRBS is still needed.
With this the session is still managed by MRBS php schema, but with more secure and better drupal integration

