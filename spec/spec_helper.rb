$LOAD_PATH.unshift(File.join(File.dirname(__FILE__), '..', 'lib'))
$LOAD_PATH.unshift(File.dirname(__FILE__))
require 'rspec'
require 'iaccessible'

# Requires supporting files with custom matchers and macros, etc,
# in ./support/ and its subdirectories.
Dir["#{File.dirname(__FILE__)}/support/**/*.rb"].each {|f| require f}

sampleApp = File.dirname(__FILE__) + '/../ext/sample/WindowsForms.exe'

RSpec.configure do |config|
  config.before(:each) do
    @pid1 = IO.popen(sampleApp).pid
    sleep 1
  end

  config.after(:each) do
    Process.kill(9, @pid1) rescue nil
  end

end
