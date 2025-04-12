pragma solidity 0.8.18;

contract DemoContract
{

    address public owner;

    struct Receivers
    {
        string name;
        uint256 tokens;
    }

    mapping(address = > Receivers) public users;

    modifier onlyOwner()
    {
        require(msg.sender == owner, "Only the contract owner can call this.");
        _;
    }

    constructor()
    {
        owner = msg.sender;
        users[owner].tokens = 85; // Owner starts with 100 tokens
    }

    function double(uint _value) public pure returns(uint)
    {
        return _value * 2;
    }

    function register(string memory _name) public
    {
        users[msg.sender].name = _name;
    }

    function giveToken(address _receiver, uint256 _amount) public onlyOwner
    {
        require(users[owner].tokens >= _amount, "Not enough tokens");
        users[owner].tokens -= _amount;
        users[_receiver].tokens += _amount;
    }

    function buyTokens() public payable
    {
        uint tokenPrice = 2 ether;
        uint tokensToBuy = msg.value / tokenPrice;

        require(tokensToBuy > 0, "Insufficient Ether to buy tokens");
        require(users[owner].tokens >= tokensToBuy, "Not enough tokens in the contract");

        users[msg.sender].tokens += tokensToBuy;
        users[owner].tokens -= tokensToBuy;
    }

    function getContractBalance() public view returns(uint)
    {
        return address(this).balance;
    }
}
