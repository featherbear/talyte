export function get (req, res) {
  return res.end(
    JSON.stringify({
      ssid: 'SSID',
      password: 'password',
      mode: 'dhcp',
      static_ip: '1.2.3.4',
      static_mask: '255.255.255.0',
      tally_host: 'tally_host',
      tally_port: 1234,
      tally_program: 'test_program'
    })
  )
}
