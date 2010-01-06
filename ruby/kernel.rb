require 'net/http'

host = Net::HTTP.new("www.kernel.org", 80)
resposta = host.get("/", nil)
print "Versões disponíveis do Kernel Linux:\n"

if (resposta.message != "OK")
	puts "Sem dados..."
	return
end

resposta.body.scan(/[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}/).uniq.each { |k|
	puts "Kernel #{k}"
}
